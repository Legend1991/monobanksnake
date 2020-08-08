#include "hamiltonsolver.h"

#include <QDebug>

HamiltonSolver::HamiltonSolver(Snake &snake): BaseSolver(snake), path_solver(snake)
{
    this->table = QVector<QVector<TableCellH>>(snake.map.num_rows);
    for (int i = 0; i < snake.map.num_rows; ++i)
        this->table[i] = QVector<TableCellH>(snake.map.num_cols, TableCellH());
//    qDebug() << "HamiltonSolver constructor";
    this->build_cycle();
}

DirecType HamiltonSolver::next_direc()
{
//    this->build_cycle();
    Pos head = this->snake.head();
    DirecType nxt_direc = this->table[head.x][head.y].direc;
    qDebug() << "HamiltonSolver::next_direc" << head.toString() << nxt_direc;
    return nxt_direc;
}

void HamiltonSolver::build_cycle()
{
    QList<DirecType> path = this->path_solver.longest_path_to_tail();
    Pos cur = this->snake.head();
    int cnt = 0;

//    qDebug() << "HamiltonSolver build_cycle 1" << cur.toString() << path.size();

    for (DirecType direc : path)
    {
//        qDebug() << "HamiltonSolver build_cycle" << Direc::toString(direc) << cur.toString();
        this->table[cur.x][cur.y].idx = cnt;
        this->table[cur.x][cur.y].direc = direc;
        cur = cur.adj(direc);
        cnt += 1;
    }

//    qDebug() << "HamiltonSolver build_cycle 2";

    cur = this->snake.tail();

    for (int i = 0; i < this->snake.len() - 1; ++i)
    {
        this->table[cur.x][cur.y].idx = cnt;
        this->table[cur.x][cur.y].direc = this->snake.direc;
        cur = cur.adj(this->snake.direc);

//        qDebug() << "HamiltonSolver build_cycle 2:" << this->snake.direc << cur.toString();
        cnt += 1;
    }
}
