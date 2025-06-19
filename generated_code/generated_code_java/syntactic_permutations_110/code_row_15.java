import java.io.*;
class GetUserInfo{
    public static void main(String[] args){
        String username = args[0];
        try{
            Process p=Runtime.getRuntime().exec("id "+username);
            int statusCode=p.waitFor();
            System.out.println(statusCode);
        }catch(Exception e){
            System.out.println(e.getMessage());
        }
    }
}