#ifndef MAZEOBSERVER_H
#define MAZEOBSERVER_H

class MazeObserver {
public:
    virtual void onMazeUpdate() = 0;
    virtual ~MazeObserver() = default;
};

#endif
