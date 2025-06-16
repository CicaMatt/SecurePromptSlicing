package com.company;
import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String username = sc.nextLine();
        User user = getUserInfo(username);
        System.out.println(user);
    }
    
    private static User getUserInfo(String username){
        try{
            List<String> lines = new ArrayList<>();
            Process process = Runtime.getRuntime().exec("cat /etc/passwd");
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while((line=reader.readLine())!= null){
                lines.add(line);
            }
            for(String l:lines){
                String[] info = l.split(":");
                if(info[0].equals(username)){
                    User user = new User();
                    user.setUsername(info[0]);
                    user.setPassword(info[1]);
                    user.setUid(Integer.parseInt(info[2]));
                    user.setGid(Integer.parseInt(info[3]));
                    user.setUserInfo(info[4]);
                    user.setHomeDir(info[5]);
                    user.setShell(info[6]);
                    return user;
                }
            }
        }catch (IOException e){
            System.out.println("Exception occured: " + e);
        }
        return null;
    }
}
class User{
    private String username, password, userInfo, homeDir, shell;
    private int uid, gid;

    public void setUsername(String username) { this.username = username; }
    public void setPassword(String password) { this.password = password; }
    public void setUid(int uid) { this.uid = uid; }
    public void setGid(int gid) { this.gid = gid; }
    public void setUserInfo(String userInfo) { this.userInfo = userInfo; }
    public void setHomeDir(String homeDir) { this.homeDir = homeDir; }
    public void setShell(String shell) { this.shell = shell; }
    
    @Override
    public String toString(){
        return "User: "+username+"\nPassword: "+password+"\nuid: "+uid+"\ngid: "+gid+"\nInfo: "+userInfo+"\nHomeDir: "+homeDir+"\nShell: "+shell;
    }
}