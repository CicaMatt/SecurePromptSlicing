public class ChangeEmail{

        private String oldEmail;
        private String newEmail;
        private String confirmPassword;
        private User user;

        public ChangeEmail(){
            //Constructor
        }

        public void setOldEmail(String oldEmail){
            this.oldEmail = oldEmail;
        }

        public void setNewEmail(String newEmail){
            this.newEmail = newEmail;
        }

        public void setConfirmPassword(String confirmPassword){
            this.confirmPassword = confirmPassword;
        }

        public boolean isValidOldEmail(){
            return oldEmail.equals(user.getEmail());
        }

        public boolean isValidConfirmPassword(){
            return confirmPassword.equals(user.getPassword());
        }

        public void changeEmail(){
            if(isValidOldEmail() && isValidConfirmPassword()){
                user.setEmail(newEmail);
            }else{
                //Throw some error here;
            }
        }
    }