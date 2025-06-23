import java.util.Scanner;
public class Main {
    public static void main(String args[]){
        String userName = "";
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter your username: ");
        userName = scanner.next();
        try{
            Process process = Runtime.getRuntime().exec("id " +userName);
            int status = process.waitFor();
            if (status == 0){
                System.out.println("Command successfull");
            }else {
                System.out.println("Command failed");
            }
        }catch(Exception e){
            System.out.println(e.getMessage());
        }
    }
}