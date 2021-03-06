(use-modules (opencog query))

(define (search-inferred-atoms)
  (let* (
        (ia-query (Get (State pln-inferred-atoms (Variable "$x"))))
        (ia (gar (cog-satisfying-set ia-query))))
    ia))

(define (get-inferred-atoms)
  (delete-duplicates (cog-get-all-nodes (search-inferred-atoms))))

(define (get-inferred-names)
  (get-names (get-inferred-atoms)))

(define (get-names atom-list)
  (map cog-name atom-list))

;; Return a list of pairs (inferred atom, name list) 
(define (get-assoc-inferred-names)
  (let ((inferred-atoms-list (cog-outgoing-set (search-inferred-atoms)))
        (gen-assoc (lambda (x) (list x (get-names (cog-get-all-nodes x)))))
        )
    (map gen-assoc inferred-atoms-list)))

(define (search-input-utterance)
  (gar (cog-satisfying-set (Get (State input-utterance (Variable "$x"))))))

(define (get-input-utterance-atoms)
  (let ((iu (search-input-utterance)))
  (if (cog-link? iu)
      (cog-outgoing-set (third (cog-outgoing-set iu)))
      '())))

(define (get-input-utterance-names)
  (get-names (get-input-utterance-atoms)))
