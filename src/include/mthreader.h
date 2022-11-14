#ifndef MTHREADER_H
#define MTHREADER_H
#include <future>
namespace business {

namespace types {

//todo: создать тип данных, который будет возвращаься из функции


} // namespace types

//todo: реализовать и протестировать статическую функцию, которая будет читать строку и парсить её

//todo: реализовать и протестировать статическую функцию,
//      который будет по вектору из ретерн велью формировать корректный тип для вывода

/**
 * @brief The MthReader class ответственный за создание многопоточных экземпляров функции
 * и последующую генерацию правильного отображения результатов выполнения.
 */
class MthReader
{
public:
    MthReader();


    //todo: реализовать мейн функцию, которая будет запускать чтение из файла и создавать экземпляры фьюч

private:
    //todo: создать тип данных, который будет хранить экзепляры фьюч
    std::future<bool> dpAsync_;



    std::future<bool> data_pack_proc( std::uint16_t cycles_n = 1 )
    {
        return std::async(std::launch::async,[cycles_n,this](){

            return true;
        });
    }


};

} // namespace business

#endif // MTHREADER_H
