import java.util.*;
public class Test{
    public static void main(String[] args) {
        //your code goes here
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the username: ");
        String name = sc.nextLine();
        System.out.print("Enter email id: ");
        String emid = sc.nextLine();
        System.out.print("Enter ssn: ");
        String ssn = sc.nextLine();
        Session ses= new Session(name,emid,ssn);
        System.out.println("Username: "+ses.getUserName());
        System.out.println("Email id: "+ses.getUserId());
        System.out.println("Ssn: "+ses.getSsn());
    }
}
class Session{
     private String name;
     private String emid;
     private String ssn;
     public Session(String name, String emid, String ssn) {
         this.name = name;
         this.emid = emid;
         this.ssn = ssn;
    }
     public String getUserName() {
         return name;
    }
     public String getUserId() {
         return emid;
    }
     public String getSsn(){
         return ssn;
     }
}