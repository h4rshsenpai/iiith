curl https://courses.iiit.ac.in/course/view.php?id=3867 |
	xmlstarlet format -H index.html 2>/dev/null |
	xmlstarlet select -t -m '//a[contains(@href,"pdf")]' -v '@href' -n |
	xargs -n 1 -I {} curl
while IFS= read -r url; do 
	file="${url%\?*}"
	file="${file##*/}"
	printf "Saving %s as %s\n" "$url" "$file"
	curl -s "$url" -o "$file"
done	
