#ifndef DIVISA_H
#define DIVISA_H

#include <string>

class Divisa
{
    private:
        
        int valor_;//cts.
        std::string tipo_;//moneda o billete
    
    public:
        
        Divisa(int valor)
        {
            valor_=valor;

            if( valor_ > 200 )
                tipo_ = "billete";
            else
                tipo_ = "moneda";
        }

       inline const int getValor()
       {
           return this->valor_;
       }

       inline const std::string getTipo()
       {
           return this->tipo_;
       }
};


#endif