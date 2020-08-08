#include "pathsolver.h"

#include <stdlib.h>
#include <time.h>

#include <QDebug>

PathSolver::PathSolver(Snake &snake): BaseSolver(snake), snake(snake), map(snake.map)
{
//    qDebug() << "PathSolver::constructor" << snake.map.num_rows;
    srand(time(NULL));
    this->table = QVector<QVector<TableCell>>(snake.map.num_rows);
    for (int i = 0; i < snake.map.num_rows; ++i)
        this->table[i] = QVector<TableCell>(snake.map.num_cols, TableCell());
}

void PathSolver::reset_table()
{
    for (int i = 0; i < this->table.size(); ++i)
    {
        for (int j = 0; j < this->table[i].size(); ++j)
        {
            this->table[i][j].reset();
        }
    }
}

QList<DirecType> PathSolver::shortest_path_to_food()
{
//    qDebug() << "PathSolver::shortest_path_to_food" << this->map.food.toString();
    return this->path_to(this->map.food, "shortest");
}

QList<DirecType> PathSolver::longest_path_to_tail()
{
//    qDebug() << "PathSolver::longest_path_to_tail" << this->snake.tail().toString();
    return this->path_to(this->snake.tail(), "longest");
}

QList<DirecType> PathSolver::path_to(const Pos &des, const QString &path_type)
{
    QList<DirecType> path;
//    qDebug() << "PathSolver path_to" << path_type << this->map.is_full();
    PointType ori_type = this->map.point(des).type;
    this->map.point(des).type = PointType::EMPTY;
//    qDebug() << "PathSolver path_to" << path_type;
    if (path_type == "shortest")
        path = this->shortest_path_to(des);
    else if (path_type == "longest")
        path = this->longest_path_to(des);
    this->map.point(des).type = ori_type;
    return path;
}

QList<DirecType> PathSolver::shortest_path_to(const Pos &des)
{
    this->reset_table();
    Pos head = this->snake.head();
    this->table[head.x][head.y].dist = 0;
    QList<Pos> queue = QList<Pos>();
    queue << head;

    while (queue.size())
    {
        Pos d = des;
        Pos cur = queue.takeFirst();
//        qDebug() << "PathSolver shortest_path_to" << queue.size() << cur.toString() << d.toString() << (cur == des);
        if (cur == des)
            return this->build_path(head, des);

        DirecType first_direc;
        if (cur == head)
            first_direc = this->snake.direc;
        else
            first_direc = this->table[cur.x][cur.y].parent.direc_to(cur);
        QList<Pos> adjs = cur.all_adj();
        for (int c1 = adjs.size() - 1; c1 > 0; c1--) {
            int c2 = rand() % (c1 + 1);
            Pos tmp = adjs[c1];
            adjs[c1] = adjs[c2];
            adjs[c2] = tmp;
        }
        for (int i = 0; i < adjs.size(); ++i)
        {
            Pos pos = adjs[i];
            if (first_direc == cur.direc_to(pos))
            {
                Pos tmp = adjs[0];
                adjs[0] = adjs[i];
                adjs[i] = tmp;
                break;
            }
        }

        for (Pos pos: adjs)
        {
            if (this->is_valid(pos))
            {
                TableCell &adj_cell = this->table[pos.x][pos.y];
                if (adj_cell.dist == INT_MAX)
                {
//                    qDebug() << adj_cell.dist << cur.toString();
                    adj_cell.parent = cur;
                    adj_cell.dist = this->table[cur.x][cur.y].dist + 1;
                    queue.append(pos);
                }
            }
        }
    }

    return QList<DirecType>();
}

QList<DirecType> PathSolver::longest_path_to(const Pos &des)
{
//    qDebug() << "PathSolver::longest_path_to 0";
    QList<DirecType> path = this->shortest_path_to(des);
//    qDebug() << "PathSolver::longest_path_to -> path size" << path.size();
    if (!path.size())
        return QList<DirecType>();

    this->reset_table();
    Pos cur = this->snake.head();
    Pos head = this->snake.head();

    this->table[cur.x][cur.y].visit = true;

    for (DirecType direc : path)
    {
        cur = cur.adj(direc);
//        qDebug() << "PathSolver::longest_path_to -> path" << Direc::toString(direc) << cur.toString();
        this->table[cur.x][cur.y].visit = true;
    }

//    idx, cur = 0, head

    int idx = 0;
    cur = head;
    while (true)
    {
        DirecType cur_direc = path[idx];
        Pos nxt = cur.adj(cur_direc);

//        qDebug() << "PathSolver::longest_path_to -> nxt:" << cur.toString() << Direc::toString(cur_direc) << nxt.toString();

        QVector<DirecType> tests;
        if (cur_direc == DirecType::LEFT || cur_direc == DirecType::RIGHT)
            tests = {DirecType::UP, DirecType::DOWN};
        else if (cur_direc == DirecType::UP || cur_direc == DirecType::DOWN)
            tests = {DirecType::LEFT, DirecType::RIGHT};

        bool extended = false;

        for (DirecType test_direc : tests)
        {
            Pos cur_test = cur.adj(test_direc);
            Pos nxt_test = nxt.adj(test_direc);

            if (this->is_valid(cur_test) && this->is_valid(nxt_test))
            {
                this->table[cur_test.x][cur_test.y].visit = true;
                this->table[nxt_test.x][nxt_test.y].visit = true;
                path.insert(idx, test_direc);
                path.insert(idx + 2, Direc::opposite(test_direc));
                extended = true;
                break;
            }
        }

        if (!extended)
        {
            cur = nxt;
            idx += 1;
            if (idx >= path.size())
                break;
        }
    }

    return path;
}

QList<DirecType> PathSolver::build_path(const Pos &src, const Pos &des)
{
    QList<DirecType> path = QList<DirecType>();
    Pos tmp = des;
    while (tmp != src)
    {
        Pos parent = this->table[tmp.x][tmp.y].parent;
        Pos s = src;
//        qDebug() << "PathSolver::build_path" << tmp.toString() << s.toString() << parent.toString();
        path.prepend(parent.direc_to(tmp));
        tmp = parent;
    }
//    qDebug() << "PathSolver::build_path -> path" << path.size() << src.x << src.y << des.x << des.y;
    return path;
}

bool PathSolver::is_valid(const Pos &pos)
{
    return this->map.is_safe(pos) && !this->table[pos.x][pos.y].visit;
}
