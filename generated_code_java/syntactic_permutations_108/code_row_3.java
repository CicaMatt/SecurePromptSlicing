import java.io.*;
class GetUserInfo {
    public static void main(String args[]) throws Exception{
        String username = "user1";
        Process p=Runtime.getRuntime().exec("getent passwd "+username);
        BufferedReader in=new BufferedReader(new InputStreamReader(p.getInputStream()));
        String line="",output="";
        while((line=in.readLine())!=null){
            output +=line;
        }
        in.close();
        System.out.println("User information for user "+username+" is :\n"+output);
    }
}