#ifndef DIRCOPY_H
#define DIRCOPY_H

#include <string>
#include <vector>

class DirCopy
{
public:
    DirCopy();
    void copy(const std::string& srcDirPath, const std::string& desDirPath);

private:
    bool make_dir (const std::string& pathName);
    bool get_src_files_name(std::vector<std::string>& fileNameList);
    void do_copy(const std::vector<std::string>& fileNameList);

private:
    std::string srcDirPath;
    std::string desDirPath;

}

#endif // DIRCOPY_H
