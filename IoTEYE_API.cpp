#include "../Headers/IoTEYE_API.h"
#include "IoTEYE_API.h"

/* TODO
*  Refactoring SendRequest:
*  It is necessary to transfer method type
*
*/

/*
*   payload - request payload
*   
*   Returns:
*   false - OK
*   true - Error
*/
bool IoTEYE_API::SendRequest(uint8_t method, const cpr::Payload &payload, cpr::Response* pResponse)
{
    // Формируем url для доступа к нужному эндпоинту
    std::string url = SERVER_URL;
    url += ':';
    url += SERVER_PORT;
    url += ENDPOINT;
    // Создаем переменную содержащую информацию об ответе
    cpr::Response r {};
    //выбор метода и отправка
    switch (method)
    {
    case POST:
        r = cpr::Post(cpr::Url{url}, payload);
        break;
    case GET:
        r = cpr::Get(cpr::Url{url}, payload );
        break;
    case PUT:
        r = cpr::Put(cpr::Url{url}, payload);
        break;
    case DELETE:
        r = cpr::Delete(cpr::Url{url}, payload);
        break;
    default:
        std::cerr << "Error: unknown method!" << std::endl;
    }
    // Если получен не 200, то выводим ошибку 
    if(r.status_code != cpr::status::HTTP_OK)
    {
        std::cerr   << "Error code: " << static_cast<uint16_t>(r.error.code) << std::endl
                    << "Error: " << r.error.message << std::endl;
        return true;
    }   
    if (pResponse != nullptr)
    *pResponse = r;
    return false;
}

bool IoTEYE_API::CreateVirtualPin(const std::string &pinNumber, const std::string &dataType)
{
    cpr::Payload p{{"userID", "someID"}};
    p.Add({"cmd", "ds"});
    //p.Add({"authToken", TOKEN});
    p.Add({"pinNumber", pinNumber});
    p.Add({"dataType", dataType});
    p.Add({"Value", "0"});
    IoTEYE_API::SendRequest(IoTEYE_API::PUT, p);
    return false;
}

bool IoTEYE_API::GetDeviceStatus()
{

    return false;
}

bool IoTEYE_API::UpdateVirtualPin(const std::string &pinNumber, double value)
{   
    cpr::Payload p{{"userID", "someID"}};
    p.Add({"cmd", "up"});
    //p.Add({"authToken", TOKEN});
    p.Add({"pinNumber", pinNumber});
    p.Add({"Value", std::to_string(value)});
    IoTEYE_API::SendRequest(IoTEYE_API::POST, p);
    return false;
}

bool IoTEYE_API::UpdateVirtualPin(const std::string &pinNumber, int value)
{
    cpr::Payload p{{"userID", "someID"}};
    p.Add({"cmd", "up"});
    //p.Add({"authToken", TOKEN});
    p.Add({"pinNumber", pinNumber});
    p.Add({"Value", std::to_string(value)});
    IoTEYE_API::SendRequest(IoTEYE_API::POST, p);
    return false;
}

bool IoTEYE_API::UpdateVirtualPin(const std::string &pinNumber, std::string &value)
{
    cpr::Payload p{{"userID", "someID"}};
    p.Add({"cmd", "up"});
    //p.Add({"authToken", TOKEN});
    p.Add({"pinNumber", pinNumber});
    p.Add({"Value", value});
    IoTEYE_API::SendRequest(IoTEYE_API::POST, p);
    return false;
}
bool IoTEYE_API::DeleteVirtualPin(const std::string &pinNumber)
{
    cpr::Payload p{{"userID", "someID"}};
    p.Add({"cmd", "DELETE"});
    //p.Add({"authToken", TOKEN});
    p.Add({"pinNumber", pinNumber});
    IoTEYE_API::SendRequest(IoTEYE_API::DELETE, p);
    return false;
}

bool IoTEYE_API::GetVirtualPin(const std::string &pinNumber)
{
    cpr::Response res {};
    cpr::Payload p{{"userID", "someID"}};
    p.Add({"pinNumber", pinNumber});
    IoTEYE_API::SendRequest(IoTEYE_API::GET, p, &res);
    if (!IoTEYE_API::SendRequest(IoTEYE_API::GET, p, &res))
    return false;
    else
    return true;
}
