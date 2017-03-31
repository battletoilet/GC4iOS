// Copyright 2016 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#pragma once

#include <memory>
#include <string>
#include <wx/panel.h>

class GameListItem;
class wxTreeCtrl;
class wxTreeEvent;

namespace DiscIO
{
class IFileSystem;
class IVolume;
}

class FilesystemPanel final : public wxPanel
{
public:
  explicit FilesystemPanel(wxWindow* parent, wxWindowID id, const GameListItem& item,
                           const std::unique_ptr<DiscIO::IVolume>& opened_iso);
  ~FilesystemPanel();

private:
  enum
  {
    ID_EXTRACT_DIR = 20000,
    ID_EXTRACT_ALL,
    ID_EXTRACT_FILE,
    ID_EXTRACT_APPLOADER,
    ID_EXTRACT_DOL,
    ID_CHECK_INTEGRITY,
  };

  void CreateGUI();
  void BindEvents();

  void PopulateFileSystemTree();
  void PopulateFileSystemTreeGC();
  void PopulateFileSystemTreeWii() const;

  void OnRightClickTree(wxTreeEvent&);
  void OnExtractFile(wxCommandEvent&);
  void OnExtractDirectories(wxCommandEvent&);
  void OnExtractHeaderData(wxCommandEvent&);
  void OnCheckPartitionIntegrity(wxCommandEvent&);

  void ExtractAllFiles(const wxString& output_folder);
  void ExtractAllFilesGC(const wxString& output_folder);
  void ExtractAllFilesWii(const wxString& output_folder);

  void ExtractSingleFile(const wxString& output_file_path) const;
  void ExtractSingleFileGC(const wxString& file_path, const wxString& output_file_path) const;
  void ExtractSingleFileWii(wxString file_path, const wxString& output_file_path) const;

  void ExtractSingleDirectory(const wxString& output_folder);
  void ExtractSingleDirectoryGC(const wxString& directory_path, const wxString& output_folder);
  void ExtractSingleDirectoryWii(wxString directory_path, const wxString& output_folder);

  void ExtractDirectories(const std::string& full_path, const std::string& output_folder,
                          DiscIO::IFileSystem* filesystem);

  wxString BuildFilePathFromSelection() const;
  wxString BuildDirectoryPathFromSelection() const;

  wxTreeCtrl* m_tree_ctrl;

  const GameListItem& m_game_list_item;
  const std::unique_ptr<DiscIO::IVolume>& m_opened_iso;

  std::unique_ptr<DiscIO::IFileSystem> m_filesystem;
};
