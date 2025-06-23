public class EmailChange {
        private String username;
        private String oldEmail;
        private String newEmail;
        private String password;
    
        public EmailChange(String username, String oldEmail) {
            this.username = username;
            this.oldEmail = oldEmail;
        }
    
        public void changeEmail(String newEmail, String password) throws EmailInvalidException, PasswordIncorrectException {
            if (!isValidEmail(newEmail)) {
                throw new EmailInvalidException("The email address is invalid");
            } else if (!isCorrectPassword(password)) {
                throw new PasswordIncorrectException("The password is incorrect");
            } else {
                this.newEmail = newEmail;
            }
        }
    
        private boolean isValidEmail(String email) {
            // code to check if the email address is valid
            return true;
        }
    
        private boolean isCorrectPassword(String password) {
            // code to check if the password is correct
            return true;
        }
    }