/*!
 * \file CPlayer.h
 * \brief Lecteur de musique de base
 * \author Wintrack
 * \version 0.1
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * \struct Str_t
 * \brief Objet chaine de caractères.
 *
 * Str_t est un petit objet de gestion de chaines de caractères.
 * La chaine se termine obligatoirement par un zéro de fin et l'objet
 * connait la taille de chaine contient !
 */
typedef struct
{
    char *sz;   /*!< Chaine avec  caractère null de fin de chaine. */
    size_t len; /*!< Taille de la chaine sz sans compter le zéro de fin. */
} Str_t;

/**
 * \enum Str_err_e
 * \brief Constantes d'erreurs.
 *
 * Str_err_e est une série de constantes prédéfinie pour diverses futures
 * fonctions de l'objet Str_t.
 */
typedef enum
{
    STR_NO_ERR,    /*!< Pas d'erreur. */
    STR_EMPTY_ERR, /*!< Erreur: Objet vide ou non initialisé. */

    NB_STR_ERR /*!< Nombre total de constantes d'erreur. */
} Str_err_e;

/**
 * \fn static Str_err_e str_destroy (Str_t ** self)
 * \brief Fonction de destruction de l'objet Str_t.
 *
 * \param self Adresse de ll'objet Str_t à détruire.
 * \return STR_NO_ERR si aucune erreur, STR_EMPTY_ERR sinon.
 */
static Str_err_e str_destroy(Str_t **self)
{
    Str_err_e err = STR_EMPTY_ERR;

    if (self != NULL && *self != NULL)
    {
        free(*self);
        *self = NULL;

        err = STR_NO_ERR;
    }

    return err;
}

/**
 * \fn static Str_t * str_new (const char * sz)
 * \brief Fonction de création d'une nouvelle instance d'un objet Str_t.
 *
 * \param sz Chaine à stocker dans l'objet Str_t, ne peut être NULL.
 * \return Instance nouvelle allouée d'un objet de type Str_t ou NULL.
 */
static Str_t *str_new(const char *sz)
{
    Str_t *self = NULL;

    if (sz != NULL && strlen(sz) > 0)
    {
        self = malloc(sizeof(*self));

        if (self != NULL)
        {
            self->len = strlen(sz);
            self->sz = malloc(self->len + 1);

            if (self->sz != NULL)
            {
                strcpy(self->sz, sz);
            }
            else
            {
                str_destroy(&self);
            }
        }
    }

    return self;
}

/**
 * \fn int main (void)
 * \brief Entrée du programme.
 *
 * \return EXIT_SUCCESS - Arrêt normal du programme.
 */
int main(void)
{
    Str_err_e err;
    Str_t *my_str = str_new("Ma chaine de caracteres !");

    if (my_str != NULL)
    {
        printf("%s\n", my_str->sz);
        printf("Taille de la chaine : %d\n", my_str->len);

        err = str_destroy(&my_str);

        if (!err)
        {
            printf("L'objet a ete libere correctement !\n");
        }
    }

    return EXIT_SUCCESS;
}