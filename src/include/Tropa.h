#include <vector>
#include <../caminho.h>
#ifndef TROPA_H
#define TROPA_H

using namespace std;

class Tropa
{
    public:
        Tropa();
        virtual ~Tropa();
        int Vida;
        vector<Caminho> Caminho;
        void DesenhaTropa();


    protected:

    private:
};

#endif // TROPA_H
