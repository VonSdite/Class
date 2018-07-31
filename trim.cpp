std::wstring trim(std::wstring s, TCHAR ch) 
{
    if (s.empty()) 
    {
        return s;
    }
 
    s.erase(0, s.find_first_not_of(ch));
    s.erase(s.find_last_not_of(ch) + 1);
    return s;
}
