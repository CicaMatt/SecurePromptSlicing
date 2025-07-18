import java.util.*;  
class UserInfo{  
public static void main(String args[]){  
try{  
Runtime r=Runtime.getRuntime();  
Process p=r.exec("cat /etc/passwd | grep "+args[0]);  
}catch(IOException e){System.out.println(e);}}}}