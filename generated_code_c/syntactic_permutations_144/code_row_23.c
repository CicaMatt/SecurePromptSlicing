int check_email(char* email)
{
    if (doesEmailExist(email) == 0)
        return 0;
    else
    {
        int result = callExternalScript();
        if (result == 1)
            return 1;
        else
            return 0;
    }
}