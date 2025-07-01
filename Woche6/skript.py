import wget
from tqdm import tqdm
cookie = "PHPSESSID=jcm1vhgnum5h6iut828cvotmi6"

for i in range(112,113):
	url = "https://judge.cpulm.org/team/problems/" + str(i)+"/text"
	print(url)
	wget.download(url)
	
	
        