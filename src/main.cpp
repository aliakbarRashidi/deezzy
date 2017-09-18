/*
The MIT License

Copyright (c) 2017-2017 Albert Murienne

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include "DeezzyApp.h"

char* get_option( char ** begin, char ** end, const std::string& option )
{
    auto** itr = std::find( begin, end, option );
    if ( itr != end && ++itr != end )
    {
        return *itr;
    }
    return nullptr;
}

int main( int argc, char *argv[] )
{
    auto* playlist = get_option( argv, argv+argc, "-p" );

    QGuiApplication app( argc, argv );

	qRegisterMetaType<TrackInfos*>("TrackInfos*");
	qmlRegisterType<DeezzyApp>("Native.DeezzyApp", 1, 0, "DeezzyApp");

    QQmlApplicationEngine engine;
#ifndef __arm__
    engine.load(QUrl(QStringLiteral("qrc:/Deezzy.qml")));
#else
    engine.load(QUrl(QStringLiteral("qrc:/Deezzy_480_320.qml")));
#endif

    if ( playlist )
    {
        auto* rootObject = engine.rootObjects().first();
        auto* deezzyObject = rootObject->findChild<DeezzyApp*>("deezzy");
        deezzyObject->setPlaylist( playlist );
    }

    return app.exec();
}
