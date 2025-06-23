import java.io.*;  
class check_mod{ 
public static void main(String[] args){ 
    String user = getQueryParameter("username");
    String pass = getQueryParameter("password");
    if (check_user_pass(user, pass)){
        response.write("true");  
    }else{
        response.write("false");
    }
}

public static boolean check_user_pass(String user, String pass){
//code to check username and password

} 
}