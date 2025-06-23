import java.util.*;
    
    public class LoginPage {
        private String userName;
        private String password;
        private String dbUserName;
        private String dbPassword;
        
        public void setUserName(String userName) {
            this.userName = userName;
        }
        
        public void setPassword(String password) {
            this.password = password;
        }
        
        public void setDbUserName(String dbUserName) {
            this.dbUserName = dbUserName;
        }
        
        public void setDbPassword(String dbPassword) {
            this.dbPassword = dbPassword;
        }
    }
    
    public class Database {
        private ArrayList<LoginPage> loginPages = new ArrayList<>();
        
        public void addLoginPage(LoginPage loginPage) {
            loginPages.add(loginPage);
        }
        
        public boolean verifyLogin(String userName, String password) {
            for (LoginPage loginPage : loginPages) {
                if (userName.equals(loginPage.getUserName()) && password.equals(loginPage.getPassword())) {
                    return true;
                }
            }
            return false;
        }
    }
    
    public class Application {
        private LoginPage loginPage = new LoginPage();
        private Database database = new Database();
        
        public void setLoginUserName(String userName) {
            loginPage.setUserName(userName);
        }
        
        public void setLoginPassword(String password) {
            loginPage.setPassword(password);
        }
        
        public void setDbUserName(String dbUserName) {
            database.setDbUserName(dbUserName);
        }
        
        public void setDbPassword(String dbPassword) {
            database.setDbPassword(dbPassword);
        }
        
        public boolean verifyLogin() {
            if (database.verifyLogin(loginPage.getUserName(), loginPage.getPassword())) {
                return true;
            }
            return false;
        }
    }
    
    public class Dashboard {
        private Application application = new Application();
        
        public void setUserName(String userName) {
            application.setLoginUserName(userName);
        }
        
        public void setPassword(String password) {
            application.setLoginPassword(password);
        }
        
        public boolean verifyLogin() {
            if (application.verifyLogin()) {
                return true;
            }
            return false;
        }
    }