#include "greedysolver.h"

#include <QDebug>

GreedySolver::GreedySolver(Snake &snake): snake(snake), map(snake.map)
{
}

DirecType GreedySolver::next_direc(bool manhattan = false)
{
    if (manhattan)
    {
        PathSolver path_solver3(this->snake);
        QList<DirecType> path_to_tail = path_solver3.longest_path_to_tail();
        if (path_to_tail.size() > 1)
        {
//            qDebug() << "GreedySolver::next_direc 0";
            return path_to_tail[0];
        }
    }

    SnakeCopy snakeCopy = this->snake.copy();
    Snake s_copy = snakeCopy.s_copy;
    Map m_copy = snakeCopy.m_copy;

    PathSolver path_solver1(this->snake);
    QList<DirecType> path_to_food = path_solver1.shortest_path_to_food();

    bool searchForLongestPath = this->snake.bodies.contains(this->snake.map.food);
    if (path_to_food.size() && !searchForLongestPath)
    {
        s_copy.move_path(path_to_food);
        if (m_copy.is_full())
        {
//            qDebug() << "GreedySolver::next_direc 1";
            return path_to_food[0];
        }

        PathSolver path_solver2(this->snake);
        QList<DirecType> path_to_tail = path_solver2.longest_path_to_tail();
        if (path_to_tail.size() > 1)
        {
//            qDebug() << "GreedySolver::next_direc 2" << this->snake.head() << Direc::toString(this->snake.direc);
            return path_to_food[0];
        }
    }

    PathSolver path_solver3(this->snake);
    QList<DirecType> path_to_tail = path_solver3.longest_path_to_tail();
    if (path_to_tail.size() > 1)
    {
//        qDebug() << "GreedySolver::next_direc 3";
        return path_to_tail[0];
    }

    Pos head = this->snake.head();
    DirecType direc = this->snake.direc;
    int max_dist = -1;
    for (Pos adj : head.all_adj())
    {
        if (this->map.is_safe(adj))
        {
            int dist = Pos::manhattan_dist(adj, this->map.food);
            if (dist > max_dist)
            {
                max_dist = dist;
                direc = head.direc_to(adj);
            }
        }
    }
//    qDebug() << "GreedySolver::next_direc 4";
    return direc;
}
