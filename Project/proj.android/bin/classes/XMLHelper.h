#ifndef __XMLHelper_H_
#define __XMLHelper_H_

#include <string>
#include "support/tinyxml2/tinyxml2.h"
#include "platform/CCFileUtils.h"

class XMLHelper {

public:
    static tinyxml2::XMLDocument* createDocHandle(std::string xmlName) {

        std::string fullPath = cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename(xmlName.c_str());

        long unsigned size = 0;
        unsigned char *data = cocos2d::CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str(), "r", &size);

        if ( ! data ) {
            assert(0);
            return NULL;
        }

        std::string text(data, data + size);

        tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument ();
        tinyxml2::XMLError parseResult = doc->Parse( text.c_str() );

        if (parseResult == tinyxml2::XML_SUCCESS) {
            // tinyxml2::XMLHandle docHandle (doc);
            return doc;
        }

        delete doc;
        return NULL;
    }
};


#endif //__XMLHelper_H_
