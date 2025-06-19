public class LoginChecker {
        private DatabaseService dbService;
    
        public LoginChecker(DatabaseService dbService) {
            this.dbService = dbService;
        }
    
        public String checkLogin(String username, String password) {
            try {
                if (this.dbService.isUserExists(username)) {
                    if (this.dbService.validatePassword(username, password)) {
                        return "success";
                    } else {
                        return "cant_login";
                    }
                } else {
                    return "cant_login";
                }
            } catch (Exception e) {
                return "internal_server_error";
            }
        }
    }