# Illustration of the dangers of git merge.

It shows how a merge of two valid codes can result in a broken one.

The `master` branch contains the original base code. It is
a small program that computes the sum `1 + 2 + .. + 10` which
gives `55`. I invite you to run `run.sh` to check you can compile
and run this program.

The branch `logging` adds 1 commit to `master`. It logs the time spent
computing the sum. The branch `optimization` also adds 1 commit to
`master`. It is supposed to be a very efficient optimization. The codes
in both branches are valid! They compile without any error and return
the expected value 55.

## The Story

To make it more real, let us imagine a story where it could happen:

Alice and Bob are two developers working in the same team. At the beginning
of the sprint, the most recent code version is in the `master` branch.
Alice's task is to implement the optimization. Bob's one is to add logging
of the time spent in function `f`. They both create their own branch from
`master`, respectively `optimization` and `logging`, and start working on
their feature.

A few days later `Alice` has finished her work. Her branch, `optimization`,
is reviewed and merged into `master`. One day later, Bob finishes his work.
The branch `logging` is reviewed. There is no conflict detected, the code
is fine so is merged in master too. A few days later, a bug is detected in
production.

## merge(Valid,Valid) = Valid ?

Merging two valid codes should produce a valid one, shouldn't it?
Actually it does not. You can try to merge these two branches in any
order you want, you'll get a bug in the code.

The problem is the changes in `logging` break an assumption the branch
`optimization` relies on. Do not blame neither Alice nor Bob. Their work
was perfectly fine. Remember that:

- This example is designed to be small. You probably do not have the
  time for a real 100k lines long real example.
- The present "optimization" is indeed silly. Clever optimizations
  relying on assumptions in the code happen **every day**!
  We want them! They make our code faster, less expansive to run, etc.
  They are valuable!
- No developer knows 100% of the code base in the projects she/he works on.
  If you know someone how does, it means either the project is very small
  or she/he is the only developer since the beginning. In the latter case,
  the project is in great danger because the day she/he leaves, the project 
  dies.

Alice could not know that some code developed independently would break
her assumption. Likewise, Bob could not be aware of Alice's assumptions
because this assumption does not exist in his branch. We really have here
two valid branches, the culprit is neither Alice nor Bob but the merge!

If you are lucky, you may catch bugs introduced by merging in your tests.
If you are not, you will have to explain your users/product owners how this
bug went into the production version.

What you should do, is reviewing the code **after** the merge. To do so,
create a temporary branch, perform the merge there, review the code
produced and if you're happy with it, then only push to master
fast-forwardly.

## Why is rebase better?

Rebasing is both dangerous, difficult and annoying! If often means resolving
many more conflicts than with a merge and if you are careless, you may erase
commits by mistake. But if you are careful, then you always know precisely
what changes you push.

Let's reconsider our story with rebases instead of merges.
When Alice push her work (branch `optimization`) to `master`. Bob rebases
his work on the new state of `master`. The bug is now present in his
branch (`logging`). So Bob has an opportunity to catch it and fix it.
So has Alice during the review.

Note: I really recommend you to create a tag before any rebase.
When you are done rebasing, compare with the tag to see if something
went wrong. If it went wrong, you can always revert the state back
to the tag:

```sh
git tag before_rebase
git diff before_rebase..HEAD
git reset --hard before_rebase
```

## The revenge of merge

When Alice's work is pushed to `master`, Bob could merge `master` into
its branch instead of rebasing. The bug would also appear letting them
the opportunities to catch it and fix it. Merging `master` into feature
branches is a bad idea because it pollutes the commit graph. On long
features, you will see several merges of `master` into the feature branch
before it is itself merged into `master`.

## Conclusion

I hope I convinced you that, despite being the easiest method,
merging is not the safest. The rule I try to apply when developing
is *you should always know precisely what changes you push*.