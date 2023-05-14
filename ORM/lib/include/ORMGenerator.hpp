#pragma once
#include <iostream>

//для этого класса тестов нет, т.к. он довольно абстрактный и его сложно проверить без совместной проверки работы в бэкендом
class ORMGenerator //класс, который генерирует фильтры, ModeManager'ы модели для бэкенда
{
public:
    void Generate();

private:
    const std::string JSON_model_file;
    void GenerateFilters();
    void GenerateModelManager();
    void GenerateModels();
    // void FillModels(); to do (сделаем, если успеем, к концу)
};