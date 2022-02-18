const char login_page[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
</head>
<body>
<form name=loginForm>
<h2>Login Form</h2>
<input name=userid placeholder='User ID'> 
<input name=pwd placeholder=Password type=Password> 
<input type=submit onclick=check(this.form) class=btn value=Login></form>
<script>
function check(form) {
if(form.userid.value=='admin' && form.pwd.value=='admin')
{window.open('/home')}
else
{alert('Error Password or Username')}
}
</script>
</body>
</html>
)rawliteral";
