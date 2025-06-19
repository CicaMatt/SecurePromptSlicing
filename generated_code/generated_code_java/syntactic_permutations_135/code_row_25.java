import java.util.*;

public class Main{
    public static void main(String args[]){
        Scanner s=new Scanner(System.in);
        System.out.println("enter username");
        String name=s.nextLine();
        System.out.println("enter password");
        String pass=s.nextLine();

        if(name.equals("admin") && pass.equals("admin")){
            return true;
        }
        else{
            return false;
        }
    }
}