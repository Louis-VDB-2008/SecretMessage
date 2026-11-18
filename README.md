# SecretMessage

Pour ce projet nous avons réalisé un programme capable de cacher et de récupérer un message dans une image.

Pour encoder l'image, le programme se base sur une ligne de commande du type: path_working_directory encode "image path" key "message"
Cela créer une copie modifiée de l'image qui sera enregistrée dans le working directory.

Pour décoder l'image, le programme se base sur une ligne de commande du type: path_working_directory decode "chemin de l'image encodée" key
Ici, on va accéder à l'image encodée et en extraire le message afin de l'afficher

# Problème majeur rencontré
La fonction ReadMessage continuait de lire le message après que celui-ci soit terminé, affichant des centaines de caractères indésirables après le message.
    ==> solution trouvée, encoder la taille du message dans l'image afin de récupérer l'information dans ReadMessage et ainsi l'arrêter à la fin du message.


# Verification
  Test                            Expected_Result              Result
wrong key in decode            crypted message                crypted message
