from flask import Flask, request, render_template, redirect
    app = Flask(__name__)

    @app.route('/buy_order', methods=['POST'])
    def buy_order():
        quantity = request.form['quantity']
        # insert into database
        return redirect("/stock_view")

    @app.route('/')
    def stock_view():
        # read from database
        return render_template('index.html', data=data)

    if __name__ == '__main__':
        app.run()