#include "Drone.h"
#include <exception>


Drone::Drone()
{
   deserialization();
}

void Drone::deserialization()
{
    std::ifstream in("parameters.txt");

    if(!in){
        throw std::runtime_error ("File error");
    }

    in >> roomWidth;
    in >> roomLenght;
    in.ignore();

    if(roomWidth <= 0 || roomLenght <= 0){
        throw std::invalid_argument ("Room can't be with negative size!");
    }
    buildRoom();

    int x, y;
    in >> x;
    in >> y;
    in.ignore();

    if(x < 0 || x >= roomLenght || y < 0 || y >= roomWidth){
        throw std::invalid_argument ("Jerry's position is invalid!");
    }
    setGoalPos({x,y});

    in >> x;
    in >> y;
    in.ignore();

    if(x < 0 || x >= roomLenght || y < 0 || y >= roomWidth){
        throw std::invalid_argument ("Tom's position is invalid!");
    }
    setCurrPos({x,y});

    int K, L;
    in >> K;
    in >> L;
    in.ignore();

    if(K < 0 || L < 0){
        throw std::invalid_argument ("Number of furnitures or painted places can't be negative!");
    }

    for(int i = 0; i < K; i++)
    {
        in >> x;
        in >> y;
        in.ignore();

        int tempY = y;

        while(in.peek() != '=')
        {            
            while(in.peek() != '\n')
            {
                char c;
                in.get(c);

                if(c == '1')
                {
                    room[x][y] = '1';
                    y++;
                }
                if(c == ' ')
                {
                    y++;
                }
            }
            if(in.peek() == '\n')
            {
                in.ignore();
                x++;
                y = tempY;
            }
        }

        while(in.peek() != '\n')
        {
            in.get();
        }in.ignore();
    }

    for(int i = 0; i < L; i++)
    {
        in >> x;
        in >> y;
        in.ignore();

        room[x][y] = 'P';
        paintPoses.push_back({x,y});
    }

    if(!in){
        throw std::runtime_error ("File error");
    }

    in.close();
}

void Drone::buildRoom()
{
    room.resize(roomLenght);

    for(int i = 0; i < roomLenght; ++i)
    {
        room[i].resize(roomWidth);
    }

    for(int i = 0; i < roomLenght; ++i)
    {
        for(int j = 0; j < roomWidth; ++j)
        {
            room[i][j] = '0';
        }
    }
}

std::vector<std::vector<char>> Drone::getRoom() const
{
    return room;
}

void Drone::setCurrPos(const Position& pos)
{
    currPos = pos;
}

void Drone::setGoalPos(const Position& pos)
{
    goalPos = pos;
}

Position Drone::getCurrPos() const
{
    return currPos;
}

Position Drone::getGoalPos() const
{
    return goalPos;
}

int Drone::getRoomLenght() const
{
    return roomLenght;
}

int Drone::getRoomWidth() const
{
    return roomWidth;
}

std::vector<Position> Drone::getPaintPoses() const
{
    return paintPoses;
}
