# SecretMessage

Pour ce projet nous avons réalisé un programme capable de cacher et de récupérer un message dans une image.bmp

Pour encoder l'image, le programme se base sur une ligne de commande du type: path_working_directory encode "image.bmp path" key "message" "encode image path"
Cela créer une copie modifiée de l'image qui sera enregistrée dans le working directory.

Pour décoder l'image, le programme se base sur une ligne de commande du type: path_working_directory decode "encoded image.bmp path" key
Ici, on va accéder à l'image encodée et en extraire le message afin de l'afficher

# Problème majeur rencontré
La fonction ReadMessage continuait de lire le message après que celui-ci soit terminé, affichant des centaines de caractères indésirables après le message.
    ==> solution trouvée, encoder la taille du message dans l'image afin de récupérer l'information dans ReadMessage et ainsi l'arrêter à la fin du message.


# Verification
  Test                                           Expected_Result                          Result
right path_working_directory                programme read                             programme read
wrong path_working_directory                void                                       ???
no path_working_directory                   void                                       ???
mode encode                                 create copie image with message            create copie image with message
mmode decode                                read message on image                      read message on image
wrong mode                                  error message                              error message "Unknown command"
no mode                                     error message                              error message "Unknown command"
right immage.bmp path                       read image                                 read image
wrong image.bmp path                        error message                              error message "Failed to open file"
if image was no .mbp                        error message                              error message "Signature invalide : ce fichier n'est pas un BMP ('BM')."
if image was smolly 54 octet                error message                              "Fichier trop petit pour contenir un en-tete BMP valide."
key in encode                               encoded the message                        encoded the message
no key in encode                            error message                              error message "Key is empty"
right key in decode                         message                                    message
wrong key in decode                         crypted message                            crypted message
message in encode                           create copie image with message            create copie image with message
no message in encode                        error message                              error message "Message is empty"
message more biggest for the imaage         error message                              error message "Message is too long"
right encode image path in encode           create immage on the path                  create image on the path with the name was givd
wrong encode image path in encode           create image on the Working directory      create image on the path of the working directory withe the name of output.bmp
encode image path with no .bmp or other .   create image .bmp                          create image with the name was name.mpb or name.[...].mbp
