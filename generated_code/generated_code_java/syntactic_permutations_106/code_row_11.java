import java.io.*;  
public class SecretInfo{ 
    public static void main(String[] args){
        String secret = "This is some super secret info"; 
        try{  
            FileWriter fw = new FileWriter("secretFile.txt"); 
            PrintWriter pw = new PrintWriter(fw); 
            pw.println(secret); 
            pw.close(); 
            Runtime.getRuntime().exec("chmod 400 secretFile.txt");
            System.out.print("Secret file: " + "secretFile.txt"); 
        }catch (IOException e){
           System.out.println(e); 
        }
    } 
}