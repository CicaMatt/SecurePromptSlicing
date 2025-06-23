import java.io.*;
    public class LoginPage {
        private String username;
        private String password;
    
        public void login() throws IOException{
            BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
            System.out.print("Enter Username: ");
            this.username = reader.readLine();
            System.out.print("Enter Password: ");
            this.password = reader.readLine();
            
    
        }
        
        public String getUsername(){
            return username;
        }
        
        public void setUsername(String username){
            this.username = username;
        }
        
        public String getPassword(){
            return password;
        }
        
        public void setPassword(String password){
            this.password = password;
        }
    }
    
    import java.io.*;
    public class LoginPageTest {
        public static void main(String[] args) throws IOException{
            System.out.println("Enter Username: ");
            BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
            String username = reader.readLine();
            System.out.println("Enter Password: ");
            String password = reader.readLine();
            
            LoginPage loginPage = new LoginPage();
            loginPage.setUsername(username);
            loginPage.setPassword(password);
        
        }
    }