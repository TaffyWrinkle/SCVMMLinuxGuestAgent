/**
 *  Copyright (c) Microsoft Corporation
 *
 *  All rights reserved.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may not
 *  use this file except in compliance with the License. You may obtain a copy
 *  of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 *  THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 *  KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED
 *  WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE,
 *  MERCHANTABLITY OR NON-INFRINGEMENT.
 *
 *  See the Apache Version 2.0 License for specific language governing
 *  permissions and limitations under the License.
 *
 **/

/**
    \file        

    \brief       Implements the assert failed method for aborting asserts.

    \date        20070618 12:35:00

*/
/*----------------------------------------------------------------------------*/

#include <scxcorelib/scxcmn.h>
#include <scxcorelib/scxassert.h>
#include <scxcorelib/scxlog.h>
#include <scxcorelib/stringaid.h>

#include <iostream>

namespace SCXCoreLib
{
/*----------------------------------------------------------------------------*/
/**
    Report assertion failed suitable for unit tests.
    
    Parameters:  c - The condition that failed (as a string).
                 f - name of file where asserttion failed.
                 l - line in file where assertion failed.
                 m - extra log message. Ignored if 0.
    Retval:      None.
        
    This method is called by the SCXASSERT macro when the assertion failes.
    This method will log using scxlog and abort as assert usually does.
    
*/
    void scx_assert_failed(const char* c, const char* f, const unsigned int l, const wchar_t* m /* = 0 */)
    {
        std::wstring errText;

        if (0 == m)
        {
            errText = L"Assertion failed: " + SCXCoreLib::StrFromMultibyte(std::string(c)) + L", file "
                + SCXCoreLib::StrFromMultibyte(std::string(f)) + L", line " + SCXCoreLib::StrFrom(l);
        }
        else
        {
            errText = L"Assertion failed: " + SCXCoreLib::StrFromMultibyte(std::string(c)) + L", file "
                + SCXCoreLib::StrFromMultibyte(std::string(f)) + L", line " + SCXCoreLib::StrFrom(l)
                + L", Message: " + m;
        }

        SCX_LOGERROR(SCXCoreLib::SCXLogHandleFactory::GetLogHandle(L"scx.core.assert"), errText);

        // Send error to stderr as well, just in case we're running in a command-line context
        std::wcerr << errText << std::endl;

        abort();
    }
} /* namespace SCXCoreLib */

/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
