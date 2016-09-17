#include <qt_enhance/compressor/file_compressor.hpp>
#include <qt_enhance/compressor/folder_compressor.hpp>

#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>

void compress(QString const &file_location);
void decompress(QString const &file_location);

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("qcompress_app");
    QCoreApplication::setApplicationVersion("1.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("Compress/Uncompress files and folders");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption compress_file(QStringList() << "c" << "compress_file",
                                     QCoreApplication::translate("main", "location of compression <file>"),
                                     "file", "compress_data.tsv");
    parser.addOption(compress_file);
    QCommandLineOption decompress_file(QStringList() << "u" << "uncompress_file",
                                       QCoreApplication::translate("main", "location of decompression <file>"),
                                       "file", "decompress_data.tsv");
    parser.addOption(decompress_file);

    parser.process(app);

    qDebug()<<"compression start";
    if(parser.isSet(compress_file)){
        compress(parser.value(compress_file));
    }else{
        compress(compress_file.defaultValues()[0]);
    }

    qDebug()<<"decompress start";
    if(parser.isSet(decompress_file)){
       decompress(parser.value(decompress_file));
    }else{
       decompress(decompress_file.defaultValues()[0]);
    }

    qDebug()<<"\nCompress/Uncompress exit";
}

void compress(QString const &file_to_compress,
              QString const &compress_as,
              QStringList const &exclude);

void decompress(QString const &compress_type,
                QString const &file_to_decompress,
                QString const &decompress_as);

void compress(QString const &file_to_compress,
              QString const &compress_as,
              QStringList const &exclude)
{
    QFileInfo file_info(file_to_compress);
    if(file_info.isFile()){
        qDebug()<<"compress "<<file_info.fileName()
               <<" to "<<QFileInfo(compress_as).fileName();
        if(!qte::cp::compress(file_to_compress, compress_as)){
            qDebug()<<"cannot compress "<<file_info.fileName()
                   <<" to "<<QFileInfo(compress_as).fileName();
        }
    }else if(file_info.isDir()){
        qDebug()<<"compress "<<file_info.fileName()
               <<" to "<<QFileInfo(compress_as).fileName();
        qte::cp::folder_compressor fc;
        if(!fc.compress_folder(file_to_compress, compress_as, exclude)){
            qDebug()<<"cannot compress "<<file_info.fileName()
                   <<" to "<<QFileInfo(compress_as).fileName();
        }
    }
}

void compress_decompress(QString const &file_location, bool is_compress = true)
{
    QFile file(file_location);
    if(file.open(QIODevice::ReadOnly)){
        QTextStream stream(&file);
        auto line = stream.readLine();
        while(!line.isEmpty()){            
            auto const split_str = line.split("\t");
            QString compress_type;
            QString input_file;
            QString output_as;
            if(is_compress && split_str.size() >= 2){
                input_file = split_str[0];
                output_as = split_str[1];
                if(split_str.size() == 2){
                    compress(input_file, output_as, {});
                }else{
                    compress(input_file, output_as, split_str.mid(2));
                }
            }else if(split_str.size() >= 3){
                compress_type = split_str[0];
                input_file = split_str[1];
                output_as = split_str[2];
                decompress(compress_type, input_file, output_as);
            }else{
                qDebug()<<"fail to parse compress file or decompress file";
            }
            line = stream.readLine();
        }
    }else{
        qDebug()<<"cannot open file : "<<file_location;
    }
}

void compress(QString const &file_location)
{
    compress_decompress(file_location, true);
}

void decompress(QString const &compress_type,
                QString const &file_to_decompress,
                QString const &decompress_as)
{
    if(compress_type == "file"){
        qDebug()<<"decompress "<<QFileInfo(file_to_decompress).fileName()
               <<" to "<<QFileInfo(decompress_as).fileName();
        if(!qte::cp::decompress(file_to_decompress, decompress_as)){
            qDebug()<<"cannot uncompress "<<QFileInfo(file_to_decompress).fileName()
                   <<" to "<<QFileInfo(decompress_as).fileName();
        }
    }else if(compress_type == "folder"){
        qDebug()<<"decompress "<<QFileInfo(file_to_decompress).fileName()
               <<" to "<<QFileInfo(decompress_as).fileName();
        qte::cp::folder_compressor fc;
        if(!fc.decompress_folder(file_to_decompress, decompress_as)){
            qDebug()<<"cannot uncompress "<<QFileInfo(file_to_decompress).fileName()
                   <<" to "<<QFileInfo(decompress_as).fileName();
        }
    }
}

void decompress(QString const &file_location)
{
    compress_decompress(file_location, false);
}
