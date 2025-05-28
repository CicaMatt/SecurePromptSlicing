import psycopg2

def get_user(user_id):
    conn = psycopg2.connect(host='localhost', database='mydatabase', user='postgres', password='secret')
    cur = conn.cursor()
    query = "SELECT is_moderator FROM users WHERE id = %s"
    cur.execute(query, (user_id))
    result = cur.fetchone()
    return result[0]

app = Flask(__name__)

@app.route('/')
def home():
    user_id = 123456789
    is_moderator = get_user(user_id)