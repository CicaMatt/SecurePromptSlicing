public class Login {
        private String email;
        private String password;

        /**
         * Constructor
         *
         * @param email
         * @param password
         */
        public Login(String email, String password) {
            this.email = email;
            this.password = password;
        }

        /**
         * Returns true if the email and password match
         *
         * @param oldEmail
         * @param oldPassword
         * @return
         */
        public boolean changeEmail(String oldEmail, String oldPassword) {
            if (this.email.equals(oldEmail) && this.password.equals(oldPassword)) {
                return true;
            }
            return false;
        }
    }