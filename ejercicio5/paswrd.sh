
# printing all the users in /etc/passwd file
while IFS=':' read -r user pass uid gid full home shell; do

    echo -e "User: $user  Password: $pass uid: $uid gid: $gid full: $full home: $home shell: $shell"
    echo "-----------------------------------"

done < /etc/passwd


# printing the users that are in /home directory
while IFS=':' read -r user pass uid gid full home shell; do

    if [[ $home == /home/* ]]; then
        echo -e "Home directory User: $user  Password: $pass uid: $uid gid: $gid full: $full home: $home shell: $shell"
    fi

done < /etc/passwd

# Bash command for getting the addresses that begin with home
# cut -d: -f6 /etc/passwd | grep home