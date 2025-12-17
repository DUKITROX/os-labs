# print all the users in /etc/passwd file
while IFS=':' read -r user pass uid gid full home shell; do
    echo -e "User: $user  Password: $pass uid: $uid gid: $gid full: $full home: $home shell: $shell"
    echo "-----------------------------------"
done < /etc/passwd

# print the users that have their home directory as a subdirectory of /home
while IFS=':' read -r user pass uid gid full home shell; do
    if [[ $home == /home/* ]]; then
        echo -e "\nHome directory User: $user  Password: $pass uid: $uid gid: $gid full: $full home: $home shell: $shell"
    fi
done < /etc/passwd

# bash command for getting the addresses that begins with home
cut -d: -f6 /etc/passwd | grep home