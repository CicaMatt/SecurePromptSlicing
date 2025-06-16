import java.util.*;
import java.io.*;
public class Login {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        boolean flag=false;
        System.out.println("Enter your username: ");
        String name=sc.nextLine();
        System.out.println("Enter your password: ");
        String pass=sc.nextLine();
        while(sc.hasNext()){
            String line = sc.readLine();
            if(line.startsWith(name)){
                String[] words=line.split(" ");
                if(words[1].equals(pass))
                    flag=true;
            }
        }
        if(flag==true){
            System.out.println("You are logged in");
        }
        else{
            System.out.println("Invalid username or password");
        }

    }
}