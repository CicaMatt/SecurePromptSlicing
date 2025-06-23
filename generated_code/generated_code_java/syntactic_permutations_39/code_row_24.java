import java.util.*;
class Login{
    public static void main(String[] args){
        Scanner sc=new Scanner(System.in);
        String user,pass;
        System.out.print("Enter Username : ");
        user=sc.nextLine();
        System.out.print("Enter Password: ");
        pass=sc.nextLine();
        if(user.equals("admin") && pass.equals("1234")){
            Session s=new Session();
            s.startSession();
        }
        else{
            System.out.println("Username or Password is incorrect");
        }
    }
}

class Session{
    public void startSession(){
        System.out.println("Welcome to the session page");
    }
}