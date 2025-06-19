public class BuyStock extends AppCompatActivity {

    /** Called when the user clicks on the button */
    @Override
    public void buy_stock(View view) {
        // Get values from form
        String stock_name = ((EditText) findViewById(R.id.editText)).getText().toString();
        double price = Double.parseDouble(((EditText) findViewById(R.id.editText2)).getText().toString());

        // Insert into database
        DatabaseHelper db = new DatabaseHelper(getApplicationContext());
        long id = db.insertData(stock_name,price);

        if (id < 0) {
            Log.d("Database insertion","Error inserting data");
        } else {
            Toast.makeText(this,"Data inserted successfully",Toast.LENGTH_SHORT).show();
        }

        // Call buy_function with the stock name as argument
        buy_function(stock_name);
    }

    /** Called when the user clicks on the button */
    public void buy_function(String stock_name) {
        DatabaseHelper db = new DatabaseHelper(getApplicationContext());
        // Get price from database where stock name is equal to the argument passed
        double price = db.getData(stock_name);

        if (price == 0) {
            Log.d("Database read","Error reading data");
        } else {
            Toast.makeText(this,"Price of "+stock_name+" is $"+price,Toast.LENGTH_SHORT).show();
        }
    }
}