;;; ===============================
 
(defparameter *sci-story*
  '((?story       -> (The Earth ?intro))
    (?intro       -> (?destroyed ?dienodie) 
                     (is struck by a giant comet and ?impact) 
                     (scientists discover ?size ?things ?who) 
                     (is attacked by ?size ?type ?things ?who))
    (?destroyed   -> (burns up and) 
                     (freezes and)  
                     (falls into the sun and))
    (?impact      -> (destroyed. The End...) 
                     (saved. The End...) 
                     (not destroyed but ?dienodie))
    (?who         -> (who ?goal))
    (?goal        -> (want our women take a few and leave. The End...) 
                     (are friendly. The End...) 
                     (?response ?rads and ?killed)
		     (look on us only as a source of norishment and ?eat))
    (?response    -> (misunderstand us and are) 
                     (understand us only too well and are) 
                     (are friendly but misunderstood and are))
    (?rads 	  -> (radioactive) 
                     (not radioactive))
    (?killed      -> (can be killed by ?killers The End...) 
                     (cannot be killed by ?killers ?twist))
    (?killers	  -> (a crowd of pesants with torches) 
                     (the Army Navy Marines or Coast Gaurd) 
                     (the atomic bomb))
    (?twist	  -> (but they die of chicken pox. The End...) 
                     (finally however ?end) 
                     (so scientist invent a weapon ?lumps) 
                     (however ?continue))
    (?continue    -> (a cute kid convinces them people are ok and ?finalend) 
                     (a priest talks to them of god and ?finalend) 
                     (?girl))
    (?girl        -> (they fall in love with a beautiful girl get married and live happily ever after. The End...))
    (?end	  -> (they kill us. The End...) 
                     (they put us under a benign dictatorship. The End...) 
                     (?eat))                     
    (?finalend    -> (they leave. The End...) 
                     (they die. The End...) 
                     (?lump))
    (?lumps       -> (and they turn into disgusting lumps. The End...))
    (?eat	  -> (they eat us. The End...))
    (?type	  -> (Martian) 
                     (Moon) 
                     (Betelgeusen) 
                     (Extragalactic))
    (?things      -> (bugs) 
                     (reptiles) 
                     (mechanical devices) 
                     (superpersons) 
                     (icky things))
    (?size        -> (tiny) 
                     (giant))
    (?dienodie    -> (everybody dies. The End...) 
                     (almost everybody dies. The End...))
))

;;; ===============================
 
(defparameter *sci-prob*
  '((?story       -> (1 The Earth ?intro))
    (?intro       -> (1 ?destroyed ?dienodie) 
                     (2 is struck by a giant comet and ?impact) 
                     (4 scientists discover ?size ?things ?who) 
                     (4 is attacked by ?size ?type ?things ?who))
    (?destroyed   -> (1 burns up and) 
                     (1 freezes and)  
                     (2 falls into the sun and))
    (?impact      -> (5 destroyed. The End...) 
                     (1 saved. The End...) 
                     (3 not destroyed but ?dienodie))
    (?who         -> (1 who ?goal))
    (?goal        -> (8 want our women take a few and leave. The End...) 
                     (2 are friendly. The End...) 
                     (5 ?response ?rads and ?killed)
		     (3 look on us only as a source of norishment and ?eat))
    (?response    -> (2 misunderstand us and are) 
                     (4 understand us only too well and are) 
                     (5 are friendly but misunderstood and are))
    (?rads 	  -> (12 radioactive) 
                     (3 not radioactive))
    (?killed      -> (2 can be killed by ?killers The End...) 
                     (7 cannot be killed by ?killers ?twist))
    (?killers	  -> (1 a crowd of pesants with torches) 
                     (4 the Army Navy Marines or Coast Gaurd) 
                     (9 the atomic bomb))
    (?twist	  -> (2 but they die of chicken pox. The End...) 
                     (5 finally however ?end) 
                     (4 so scientist invent a weapon ?lumps) 
                     (9 however ?continue))
    (?continue    -> (1 a cute kid convinces them people are ok and ?finalend) 
                     (2 a priest talks to them of god and ?finalend) 
                     (6 ?girl))
    (?girl        -> (1 they fall in love with a beautiful girl get married and live happily ever after. The End...))
    (?end	  -> (10 they kill us. The End...) 
                     (4 they put us under a benign dictatorship. The End...) 
                     (2 ?eat))                     
    (?finalend    -> (1 they leave. The End...) 
                     (2 they die. The End...) 
                     (3 ?lump))
    (?lumps       -> (1 and they turn into disgusting lumps. The End...))
    (?eat	  -> (1 they eat us. The End...))
    (?type	  -> (12 Martian) 
                     (3 Moon) 
                     (1 Betelgeusen) 
                     (7 Extragalactic))
    (?things      -> (2 bugs) 
                     (5 reptiles) 
                     (3 mechanical devices) 
                     (3 superpersons) 
                     (1 icky things))
    (?size        -> (5 tiny) 
                     (10 giant))
    (?dienodie    -> (6 everybody dies. The End...) 
                     (1 almost everybody dies. The End...))
))
