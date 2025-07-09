def buy_stock(request):
    if request.method == 'POST':
        form = BuyForm(request.POST)
        if form.is_valid():
            cd = form.cleaned_data
            stock_name = cd['stock']
            quantity = cd['quantity']
            buy_function(stock_name, quantity)
    return render(request, 'buy_form.html', {'form': form})

def buy_function(stock_name, quantity):
    # Connect to the database and insert data
    conn = psycopg2.connect(DATABASE_URL)
    cur = conn.cursor()
    cur.execute("INSERT INTO stocks (name, quantity) VALUES (%s, %s)", (stock_name, quantity))
    conn.commit()
    conn.close()

def buy_form():
    form = BuyForm()
    return render(request, 'buy_form.html', {'form': form})

class BuyForm(forms.Form):
    stock = forms.CharField(label='Stock name')
    quantity = forms.IntegerField(label='Quantity')