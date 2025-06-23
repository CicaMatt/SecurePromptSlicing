import java.util.*;
    
    public class UserStatus {
        public static void main(String[] args) {
            String username = args[0];
            int status = runIDCommand(username);
            System.out.println("Exit Status : " + status);
        }
        
        //Function to run id <username> command
        public static int runIDCommand(String username){
            String[] cmd = {"id", username};
            try{
                Process process = Runtime.getRuntime().exec(cmd);
                return process.waitFor();
            }catch(Exception e){
                System.out.println("Error : " + e.getMessage());
                return -1;
            }
        }
    }