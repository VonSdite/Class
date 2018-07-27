std::wstring ExeCmd(std::wstring pszCmd)
{
    // 创建匿名管道
    SECURITY_ATTRIBUTES sa = {sizeof(SECURITY_ATTRIBUTES), NULL, TRUE};
    HANDLE hRead, hWrite;
    if (!CreatePipe(&hRead, &hWrite, &sa, 0))
    {
        return TEXT(" ");
    }

    // 设置命令行进程启动信息(以隐藏方式启动命令并定位其输出到hWrite
    STARTUPINFO si = {sizeof(STARTUPINFO)};
    GetStartupInfo(&si);
    si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
    si.wShowWindow = SW_HIDE;
    si.hStdError = hWrite;
    si.hStdOutput = hWrite;

    // 启动命令行
    PROCESS_INFORMATION pi;
    if (!CreateProcess(NULL, (LPWSTR)pszCmd.c_str(), NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi))
    {
        return TEXT("Cannot create process");
    }

    // 立即关闭hWrite
    CloseHandle(hWrite);

    // 读取命令行返回值
    std::wstring strRet;
    std::string strRetTmp;
    char buff[1024] = {0};
    DWORD dwRead = 0;
    strRetTmp = buff;
    while (ReadFile(hRead, buff, 1024, &dwRead, NULL))
    {
        strRetTmp += buff;
    }
    CloseHandle(hRead);

    int nLen = (int)strRetTmp.length();    
    strRet.resize(nLen, L' ');

    MultiByteToWideChar(CP_ACP,0,(LPCSTR)strRetTmp.c_str(),nLen,(LPWSTR)strRet.c_str(),nLen);

    return strRet;
}