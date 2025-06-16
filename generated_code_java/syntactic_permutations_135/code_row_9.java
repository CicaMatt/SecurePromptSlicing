import java.io.*;
    
    public class CheckMod {
        
        public static void main(String[] args) throws IOException {
            String userName = getUserName();
            String passWord = getPassword();
            boolean isCorrect = checkMod(userName,passWord);
            System.out.println("Check Mod: "+isCorrect);
        }
        
        public static String getUserName() throws IOException {
            BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
            return reader.readLine();
        }
        
        public static String getPassword() throws IOException {
            BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
            return reader.readLine();
        }
        
        public static boolean checkMod(String userName,String passWord) {
            if (userName.equals("admin") && passWord.equals("123456")){
                return true;
            }
            else 
                return false;
            
        }
    }