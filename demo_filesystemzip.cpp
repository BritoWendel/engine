#include "Window.hpp"
#include "Graphics.hpp"
#include "FileInfo.hpp"
#include "FilesystemZip.hpp"

#include <iostream>
#include <string>

int main(int argc, char* argv[]) 
{
    std::string zipPath = "./teste.zip";
    std::string zipBasePath =  std::string("./");
    FilesystemZip* fs = new FilesystemZip(zipPath, zipBasePath);
    FileInfo arquivo("teste/arquivo_novo.txt");

    fs->initialize();

    FileInterface* file = fs->openFile(arquivo, FileInterface::Mode::Read);

    //Posicionado no comeco do primeiro sample
    //O tamanho de um sample
    //Quantos canais de audio o wave tem

    if (file->isOpen())
    {
        char teste[35] = {};
        teste[34] = '\0';
        uint64_t byteslidos = file->read(reinterpret_cast<uint8_t*>(teste), 34);
        std::cout << "Texto: " << teste << std::endl;
        std::cout << "Bytes lidos: " << byteslidos << std::endl;

        // char* message = static_cast<char*>("mensagem estranha");
        // uint64_t pos = file->seek(0, FileInterface::Origin::End);
        // std::cout << pos << std::endl;
        // uint64_t bytesescritos = file->write(reinterpret_cast<uint8_t*>(message), 17);
        // std::cout << "Bytes escritos: " << bytesescritos << std::endl;
    }
    
    fs->closeFile(file);

    delete file;

    fs->shutdown();

    delete fs;

    return 0;    
}

