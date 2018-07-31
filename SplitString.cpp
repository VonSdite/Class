std::vector<std::wstring> SplitString(const std::wstring s, const std::wstring c)
{
    std::vector<std::wstring> v;
    std::wstring::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(std::wstring::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2-pos1));

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length())
        v.push_back(s.substr(pos1));
    return v;
}