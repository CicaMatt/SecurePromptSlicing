public class EmailChecker {
        private String email;

        public EmailChecker(String email) {
            this.email = email;
        }

        public int checkEmail() {
            if (doesntExist()) {
                return 2;
            } else {
                if (unsubscribe()) {
                    return 1;
                } else {
                    return 0;
                }
            }
        }

        private boolean unsubscribe() {
            // Script that unsubscribes the email
            return false;
        }

        private boolean doesntExist() {
            // Check if the email exists in the database
            return true;
        }    
    }