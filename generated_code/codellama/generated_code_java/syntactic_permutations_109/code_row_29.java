import java.io.*;
public class UserInfo{
    public static String getUserInfo(String userName){
        String userInfo = "";
        try{
            Process process = Runtime.getRuntime().exec("cat /etc/passwd | grep" + userName);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            userInfo = reader.readLine();
        }catch(Exception e){}
        return userInfo;
    }
    
    public static void main(String[] args) {
        String userName = "";
        if (args.length > 0)
            userName = args[0];
        
        System.out.println("User Information: " + getUserInfo(userName));
    }
}