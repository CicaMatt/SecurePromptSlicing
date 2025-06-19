public class Chat{
        private String[] users = new String[10];
        private String[] messages = new String[10];
        private int numUsers = 0;
        public void post(String username, String message){
            if (numUsers < 10){
                users[numUsers] = username;
                messages[numUsers] = message;
                numUsers++;
                insert_user_message_in_db(username, message);
            }else {
                throw new IllegalArgumentException("Maximum number of users reached");
            }
            redirect_to_main_page();
        }

    private void insert_user_message_in_db(String username, String message){
        //Connect to a database and store the data
    }

    public void redirect_to_main_page(){
        //Redirects the user to the main page
    }

}