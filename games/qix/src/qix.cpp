/*
** EPITECH PROJECT, 2020
** qix
** File description:
** qix
*/

#include "qix.hpp"

void qix::ennemiesturn(int x, std::size_t i)
{
    if (x != 0)
        ennemies[i].y = ((ennemies[i].y - 1 > -1) && (map[ennemies[i].y - 1][ennemies[i].x] == '#') ? ennemies[i].y - 1 : ennemies[i].y + 1);
    else
        ennemies[i].x = ((ennemies[i].x - 1 > -1) && (map[ennemies[i].y][ennemies[i].x - 1] == '#') ? ennemies[i].x - 1 : ennemies[i].x + 1);
}

void qix::ennemiesmove()
{
    int x = 0;
    int y = 0;

    for (std::size_t i = 0; i != ennemies.size(); i++) {
        x = ennemies[i].xb;
        y = ennemies[i].yb;
        ennemies[i].xb = ennemies[i].x;
        ennemies[i].yb = ennemies[i].y;
        if ((ennemies[i].x - x) < 0 && (ennemies[i].x - 1) > -1 && map[ennemies[i].y][ennemies[i].x - 1] == '#')
            ennemies[i].x--;
        else if ((ennemies[i].x - x) > 0 && (ennemies[i].x + 1) < 102 && map[ennemies[i].y][ennemies[i].x + 1] == '#')
            ennemies[i].x++;
        else if ((ennemies[i].y - y) < 0 && (ennemies[i].y - 1) > -1 && map[ennemies[i].y - 1][ennemies[i].x] == '#')
            ennemies[i].y--;
        else if ((ennemies[i].y - y) > 0 && (ennemies[i].y + 1) < 52 && map[ennemies[i].y + 1][ennemies[i].x] == '#')
            ennemies[i].y++;
        else
            ennemiesturn((ennemies[i].x - x), i);
    }
}

int qix::interprete_input(int input)
{
    p.xb = p.x;
    p.yb = p.y;
    if (input == 'z' && p.y != 0 && map[p.y - 1][p.x] != '*' && map[p.y - 1][p.x] != 'a')
        p.y--;
    if (input == 's' && p.y < 51 && map[p.y + 1][p.x] != '*' && map[p.y + 1][p.x] != 'a')
        p.y++;
    if (input == 'q' && p.x != 0 && map[p.y][p.x - 1] != '*' && map[p.y][p.x - 1] != 'a')
        p.x--;
    if (input == 'd' && p.x < 101 && map[p.y][p.x + 1] != '*' && map[p.y][p.x + 1] != 'a')
        p.x++;
    if (input == 'e')
        return (-1);
    if (map[p.y][p.x] == ' ' && map[p.yb][p.xb] == '#') {
        count.x = p.xb;
        count.y = p.yb;
    }
    return (0);
}

int qix::countdistance(player tmp, bool t)
{
    int nb = 0;
    int x = 0;
    int y = 0;

    for (; tmp.x != p.x || tmp.y != p.y; nb++) {
        if (nb != 0 && t)
            map[tmp.y][tmp.x] = 'a';
        x = tmp.xb;
        y = tmp.yb;
        tmp.xb = tmp.x;
        tmp.yb = tmp.y;
        if ((tmp.x - x) < 0 && (tmp.x - 1) > -1 && map[tmp.y][tmp.x - 1] == '#')
            tmp.x--;
        else if ((tmp.x - x) > 0 && (tmp.x + 1) < 102 && map[tmp.y][tmp.x + 1] == '#')
            tmp.x++;
        else if ((tmp.y - y) < 0 && (tmp.y - 1) > -1 && map[tmp.y - 1][tmp.x] == '#')
            tmp.y--;
        else if ((tmp.y - y) > 0 && (tmp.y + 1) < 52 && map[tmp.y + 1][tmp.x] == '#')
            tmp.y++;
        else {
            x = tmp.x - x;
            if (x != 0)
                tmp.y = ((tmp.y - 1 > -1) && (map[tmp.y - 1][tmp.x] == '#') ? tmp.y - 1 : tmp.y + 1);
            else
                tmp.x = ((tmp.x - 1 > -1) && (map[tmp.y][tmp.x - 1] == '#') ? tmp.x - 1 : tmp.x + 1);
        }
    }
    return (nb);
}

void qix::changemap()
{
    player tmp;
    player tmpbis;
    int s = 0;

    tmp.x = count.x;
    tmp.y = count.y;
    tmp.xb = count.x;
    tmp.yb = count.y;
    tmpbis = tmp;
    if ((tmp.x - 1) >= 0 && map[tmp.y][tmp.x - 1] == '#') {
        tmp.xb--;
        s = 1;
    } if ((tmp.x + 1) <= 101 && map[tmp.y][tmp.x + 1] == '#') {
        if (s != 1)
            tmp.xb++;
        else
            tmpbis.xb++;
        s = 1;
    } if ((tmp.y - 1) >= 0 && map[tmp.y - 1][tmp.x] == '#') {
        if (s != 1)
            tmp.yb--;
        else
            tmpbis.yb--;
        s = 1;
    } if ((tmp.y + 1) <= 51 && map[tmp.y + 1][tmp.x] == '#')
        tmpbis.yb++;
    count.nbo = countdistance(tmp, false);
    count.nbt = countdistance(tmpbis, false);
    if (count.nbo < count.nbt)
        countdistance(tmp, true);
    else
        countdistance(tmpbis, true);
    for (std::size_t i = 0; i != map.size(); i++)
        std::replace( map[i].begin(), map[i].end(), '*', '#');
    for (std::size_t i = 0; i != map.size(); i++)
        for (std::size_t j = 0; j != map[i].length(); j++) {
            if (map[i][j] == 'a')
                addnewborder(i, j);        
        }
}

void qix::addnewborder(std::size_t i, std::size_t j)
{
    if (j > 0 && map[i][j - 1] == ' ') {
        map[i][j - 1] = 'a';
        addnewborder(i, j-1);
    } if ((j + 1) < map[i].length() && map[i][j + 1] == ' ') {
        map[i][j + 1] = 'a';
        addnewborder(i, j+1);
    } if (i > 0 && map[i - 1][j] == ' ') {
        map[i - 1][j] = 'a';
        addnewborder(i-1, j);
    } if ((i + 1) < map.size() && map[i + 1][j] == ' ') {
        map[i + 1][j] = 'a';
        addnewborder(i+1, j);
    }
}

void qix::bossmovement()
{
    int nb = std::rand()%4+1;

    b.nb++;
    if (b.nb == b.animeboss.size())
        b.nb = 0;
    if (nb == 1 && (b.x + 7) < 101)
        b.x++;
    else if (nb ==2 && (b.x) > 1)
        b.x--;
    else if (nb == 3  && (b.y + 7) < 51)
        b.y++;
    else if ((b.y) > 1)
        b.y--;
}

void printback(char c, std::size_t i, std::size_t j)
{
    std::string s = "";
    s += c;

    if (c == '1') {
        attron(COLOR_PAIR(2));
        mvprintw(i, j, s.c_str()); 
        attroff(COLOR_PAIR(2));
    } else if (c == '3') {
        attron(COLOR_PAIR(4));
        mvprintw(i, j, s.c_str()); 
        attroff(COLOR_PAIR(4));
    } else if (c == '0') {
        attron(COLOR_PAIR(7));
        mvprintw(i, j, s.c_str()); 
        attroff(COLOR_PAIR(7));
    } else if (c == '2') {
        attron(COLOR_PAIR(6));
        mvprintw(i, j, s.c_str()); 
        attroff(COLOR_PAIR(6));
    } else if (c == '5') {
        attron(COLOR_PAIR(3));
        mvprintw(i, j, s.c_str()); 
        attroff(COLOR_PAIR(3));
    } else if (c == '7') {
        attron(COLOR_PAIR(5));
        mvprintw(i, j, s.c_str()); 
        attroff(COLOR_PAIR(5));
    } else if (c == '4') {
        attron(COLOR_PAIR(8));
        mvprintw(i, j, s.c_str()); 
        attroff(COLOR_PAIR(8));
    } else if (c == '6') {
        attron(COLOR_PAIR(9));
        mvprintw(i, j, s.c_str()); 
        attroff(COLOR_PAIR(9));
    }
}

void qix::display()
{
    if (map[p.y][p.x] == '#' && map[p.yb][p.xb] != '#')
        changemap();
    if (map[p.y][p.x] == ' ')
        map[p.y][p.x] = '*';
    for (std::size_t i = 0; i != map.size(); i++)
        mvprintw(i, 0, map[i].c_str());
    mvprintw(p.y, p.x, p.c.c_str());
    attron(COLOR_PAIR(1));
    for (std::size_t i = 0; i != ennemies.size(); i++)
        mvprintw(ennemies[i].y, ennemies[i].x, ennemies[i].c.c_str());
    attroff(COLOR_PAIR(1));
    for (std::size_t i = 0; i != b.animeboss[b.nb].size(); i++)
        mvprintw(i + b.y, 0 + b.x, b.animeboss[b.nb][i].c_str());
    bossmovement();
    for (std::size_t i = 0; i != background.size(); i++)
        for (std::size_t j = 0; j != background[i].length(); j++)
            if (map[i][j] == 'a')
                printback(background[i][j], i ,j);
}

void qix::addEnnemies(int x, int y, std::string s)
{
    player e;

    e.c = s;
    e.x = x;
    e.y = y;
    e.xb = x;
    e.yb = y - 1;
    ennemies.push_back(e);
}

void qix::setbackground()
{
    std::ifstream _file("background", std::ios::in);
    std::string buffer;

    while (std::getline(_file, buffer, '\n'))
        background.push_back(buffer);
}

void qix::addboss()
{
    std::ifstream _file("monster", std::ios::in);
    std::string buffer;
    std::vector<std::string> sprite;
    int nb = 0;

    while (std::getline(_file, buffer, '\n')) {
        sprite.push_back(buffer);
        nb++;
        if (nb % 7 == 0) {
            b.animeboss.push_back(sprite);
            sprite.clear();
        }
    }
}

qix::qix()
{
    std::string str = "";

    for (int i = 0; i != 102; i++)
        str += "#";
    map.push_back(str);
    for (int i = 1; i != 51; i++) {
        str = "#";
        for (int j = 1; j != 101; j++)
            str += " ";
        str += "#";
        map.push_back(str);
    }
    str = "";
    for (int i = 0; i != 102; i++)
        str += "#";
    map.push_back(str);
    addEnnemies(0, 25, "X");
    addEnnemies(101, 25, "X");
    setbackground();
    addboss();
}