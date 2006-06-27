// Copyright (c) 2005, Niels Martin Hansen
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//   * Redistributions of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//   * Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//   * Neither the name of the Aegisub Group nor the names of its contributors
//     may be used to endorse or promote products derived from this software
//     without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// -----------------------------------------------------------------------------
//
// AEGISUB
//
// Website: http://aegisub.cellosoft.com
// Contact: mailto:jiifurusu@gmail.com
//

#include <wx/string.h>
#include <wx/datetime.h>
#include "version.h"

#ifdef __WINDOWS__
// This include is generated by build/make-svn-rev-header.py
// That script should be run before every build is initiated
#include "build/svn-revision.h"

// Either create a build/build-credit.h file defining BUILD_CREDIT,
// or define it during compilation of this file
#ifndef BUILD_CREDIT
#include "build/build-credit.h"
#endif

#else

#ifndef BUILD_SVN_REVISION
#define BUILD_SVN_REVISION 0
#endif
#endif

#define BUILD_TIMESTAMP _T(__DATE__) _T(" ") _T(__TIME__)

// If the BUILD_SVN_REVISION happens to be negative, the build is assumed to be a public-release build (ie. not prerel)
// So manually edit build/svn-revision.h to match that, when doing such a build, or add some other magic to do that.

struct VersionInfoStruct {
	// Some raw data
	wxChar *VersionNumber;
	bool IsDebug;
	bool IsRelease;
	int SvnRev;
	wxChar *BuildTime;
	wxChar *BuildCredit;

	// Nice strings for display
	wxString LongVersionString;
	wxString ShortVersionString;

	// Generate the above data
	VersionInfoStruct() {
		wxString SCMStr, VersionStr;

		// Update this whenever a new version is release
		VersionNumber = _T("v1.10");
#ifdef _DEBUG
		IsDebug = true;
#else
		IsDebug = false;
#endif
		SvnRev = BUILD_SVN_REVISION;
		BuildTime = BUILD_TIMESTAMP;
		BuildCredit = _T(BUILD_CREDIT);

		if (SvnRev > 0)
			SCMStr = wxString::Format(_T("SVN r%d"), SvnRev);
#ifdef BUILD_DARCS
		else
			SCMStr = _T("darcs");
#endif

		IsRelease = SvnRev < 0;
		VersionStr = wxString::Format(_T("%s %s"), VersionNumber, IsRelease ? _T("beta") : _T("PRE-RELEASE"));

		LongVersionString = wxString::Format(_T("%s (%s%s, %s)"), VersionStr.c_str(), IsDebug ? _T("debug, ") : _T(""), SCMStr.c_str(), BuildCredit);
		ShortVersionString = wxString::Format(_T("%s %s%s"), VersionStr.c_str(), SCMStr.c_str(), IsDebug ? _T(" debug") : _T(""));

		if (IsRelease && !IsDebug)
			ShortVersionString = LongVersionString = VersionStr;
	}
};


VersionInfoStruct versioninfo;


wxString GetAegisubLongVersionString() {
	return versioninfo.LongVersionString;
}

wxString GetAegisubShortVersionString() {
	return versioninfo.ShortVersionString;
}

wxString GetAegisubBuildTime() {
	return versioninfo.BuildTime;
}

wxString GetAegisubBuildCredit() {
	return versioninfo.BuildCredit;
}
