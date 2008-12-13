/*!
	@file
	@author		Albert Semenov
	@date		09/2008
	@module
*/
#ifndef __MYGUI_LANGUAGE_MANAGER_H__
#define __MYGUI_LANGUAGE_MANAGER_H__

#include "MyGUI_Prerequest.h"
#include "MyGUI_Instance.h"
#include "MyGUI_XmlDocument.h"

namespace MyGUI
{

	typedef std::vector<std::string> VectorString;
	typedef std::map<std::string, VectorString> MapListString;
	typedef std::map<std::string, std::string> MapString;
	typedef std::map<Ogre::UTFString, Ogre::UTFString> MapLanguageString;

	// делегат для смены оповещения смены языков
	typedef delegates::CMultiDelegate1<const std::string &> MultiDelegate_String;

	class MYGUI_EXPORT LanguageManager
	{
		MYGUI_INSTANCE_HEADER(LanguageManager);

	public:
		void initialise();
		void shutdown();

	public:

		/** Load additional MyGUI *_language.xml file */
		bool load(const std::string & _file, const std::string & _group = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

		void _load(xml::xmlNodePtr _node, const std::string & _file, Version _version);

		/** Return true if language _name exist */
		bool isLanguageExist(const std::string & _name) { return mMapFile.find(_name) != mMapFile.end(); }
		/** Set current language for replacing #{} tags */
		bool setCurrentLanguage(const std::string & _name);
		/** Get current language */
		std::string getCurrentLanguage() { return mCurrentLanguage != mMapFile.end() ? mCurrentLanguage->first : ""; }

		/** Replace all tags #{tagname} in _line with appropriate string dependent
		on current language or keep #{tagname} if 'tagname' not found found */
		Ogre::UTFString replaceTags(const Ogre::UTFString & _line);

		/** Get tag value */
		Ogre::UTFString getTag(const Ogre::UTFString & _tag);

		/** Add user tag */
		void addUserTag(const Ogre::UTFString & _tag, const Ogre::UTFString & _replace) { mUserMapLanguage[_tag] = _replace; }

		/** Delete all user tags */
		void clearUserTags() { mUserMapLanguage.clear(); }

		/** Event : Change current language.\n
			info : \n
			signature : void method(const std::string & _language);
			@param _language Current language.
		*/
		MultiDelegate_String eventChangeLanguage;

	private:
		void loadLanguage(const VectorString & _list, const std::string & _group);
		bool loadLanguage(const std::string & _file, const std::string & _group);
		void _loadLanguage(std::ifstream & _stream);
		void _loadLanguage(const Ogre::DataStreamPtr& stream);


	private:
		MapListString mMapFile;
		MapListString::const_iterator mCurrentLanguage;

		MapLanguageString mMapLanguage;
		MapLanguageString mUserMapLanguage;
	};

} // namespace MyGUI

#endif // __MYGUI_LANGUAGE_MANAGER_H__
